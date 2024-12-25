FROM pytorch/pytorch:2.3.0-cuda12.1-cudnn8-runtime

RUN pip3 install \
    transformers \
    lightning \
    pandas \
    "cherche[gpu]" \
    tira \
    && pip3 install --no-deps ir-datasets \
    && pip cache purge \
    && huggingface-cli download sentence-transformers/all-MiniLM-L6-v2
