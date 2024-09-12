#!/usr/bin/env python3
import argparse
from tira.third_party_integrations import ir_datasets, persist_and_normalize_run
from tira.rest_api_client import Client as tira
import pandas as pd
from tqdm import tqdm
import cherche.rank as rank
from sentence_transformers import SentenceTransformer


def main(dataset_id, top_k):
    # Load dataset
    dataset = ir_datasets.load(dataset_id)
    docs_store = dataset.docs_store()
    queries = {i.query_id: i.default_text() for i in dataset.queries_iter()}
    
    # we have no pyterrier in this docker image, so we load the previous stage via pandas
    plaid_x = tira().get_run_output('reneuir-2024/reneuir-baselines/plaid-x-retrieval', dataset_id)
    plaid_x = pd.read_csv(plaid_x + '/run.txt', sep="\s+", names=["qid", "q0", "docid", "rank", "score", "system"], dtype={"qid": str, "docid": str})
    plaid_x = plaid_x[plaid_x['rank'] <= top_k]

    cherche_re_ranker = rank.Encoder(key="id", on=["text"], encoder=SentenceTransformer("sentence-transformers/all-MiniLM-L6-v2").encode, k=top_k)
    ranking = []

    for qid, query in tqdm(queries.items(), 'Rerank Queries'):
        documents = plaid_x[plaid_x['qid'] == qid]['docid']
        documents = [{"id": docid, "text": docs_store.get(docid).default_text()} for docid in documents]
        for result in cherche_re_ranker(q=query, documents=documents):
            ranking += [{"qid": qid, "docno": result['id'], "score": result['similarity']}]
    
    ranking = pd.DataFrame(ranking)
    persist_and_normalize_run(ranking, 'plaid-miniLML6')



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run re-rank plaid-x with chercher.")
    parser.add_argument("--dataset_id", type=str, default="reneuir-2024/dl-top-1000-docs-20240701-training", required=False)
    parser.add_argument("--top-k", type=int, default=100, required=False)
    args = parser.parse_args()

    main(args.dataset_id, args.top_k)
