#!/usr/bin/env python3
import argparse
import pandas as pd
from tira.third_party_integrations import ir_datasets, persist_and_normalize_run
import cherche.retrieve as retrieve
import cherche.rank as rank
from tqdm import tqdm
from sentence_transformers import SentenceTransformer


def main(dataset_path, k):
    # Load dataset
    dataset = ir_datasets.load(dataset_path)

    docs = list(dataset.docs_iter())
    docs_store = dataset.docs_store()
    queries = {i.query_id: i.default_text() for i in dataset.queries_iter()}

    # Print a few documents and queries to verify
    for doc in docs[:1]:
        print(f"Document ID: {doc.doc_id}\nDocument Text: {doc.default_text()}\n-----------")

    for query in list(queries)[:1]:
        print(f"Query ID: {query}\nQuery Text: {queries[query]}\n-----------")

    documents = [{"id": doc.doc_id, "text": doc.default_text()} for doc in dataset.docs_iter()]
    print(f'Index {len(documents)} documents.')

    # Initial retrieval with Lunr
    retriever = retrieve.Lunr(key="id", on=["text"], documents=documents, k=k)

    # Run initial retrieval
    run = {
        query_id: {x["id"]: float(x["similarity"]) for x in retriever(query)}
        for query_id, query in tqdm(queries.items(), 'Retrieval with Lunr')
    }

    # Re-rank using neural model
    ranker = rank.Encoder(key="id", on=["text"], encoder=SentenceTransformer("sentence-transformers/all-MiniLM-L6-v2").encode, k=k)
    ranking = []

    for qid, query in tqdm(queries.items(), 'Rerank Queries'):
        documents = list(run[qid].keys())
        documents = [{"id": docid, "text": docs_store.get(docid).default_text()} for docid in documents]
        for result in ranker(q=query, documents=documents):
            ranking += [{"qid": qid, "docno": result['id'], "score": result['similarity']}]
    
    ranking = pd.DataFrame(ranking)

    # Write re-ranking results to file
    persist_and_normalize_run(ranking, 'Lunr-miniLML6')


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run retrieval and ranking on a dataset.")
    parser.add_argument("dataset_id", type=str, help="Path to the dataset, e.g. reneuir-2024/dl-top-10-docs-20240701-training")
    parser.add_argument("--top-k", type=int, default=100, required=False)
    args = parser.parse_args()

    main(args.dataset_id, args.top_k)