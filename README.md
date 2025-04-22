# OGrad

> An interactive frontend to design neural networks layer-by-layer and submit jobs for training.

The application is deployed and can be found [here](http://vcm-47087.vm.duke.edu)

This repository contains two key components:

1. **Macrograd UI** — A frontend interface to visually construct neural networks and submit training jobs to the backend.
2. **VGGNet Implementation** — A from-scratch implementation of the VGGNet architecture using PyTorch, with a custom CrossEntropy loss and AdamW optimizer.


### How to run

- Frontend
```bash
cd frontend
npm install
npm run dev
```

- Backend
```bash
cd api
flask run api
```

- Deep learning module
```bash
cd deep-learning
python main.py
```

