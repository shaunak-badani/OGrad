from fastapi import FastAPI, BackgroundTasks
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import uuid
from typing import Dict, Any
import time


tasks_progress: Dict[str, Dict[str, Any]] = {}

app = FastAPI()

# app.add_middleware(
#     CORSMiddleware,
#     allow_origins=["http://localhost:5173"],  # React dev server
#     allow_credentials=True,
#     allow_methods=["*"],
#     allow_headers=["*"],
# )

class TaskResponse(BaseModel):
    task_id: str


@app.post("/start_task")
async def start_task(background_tasks: BackgroundTasks):
    """Start a new task and return its ID"""
    task_id = str(uuid.uuid4())
    tasks_progress[task_id] = {"progress": 0}

    background_tasks.add_task(process_task, task_id)
    return {"message" : "success"}

def process_task(task_id: str):
    """Background task to submit ML job"""
    total_steps = 20
    for step in range(1, total_steps + 1):
        time.sleep(0.5)
        progress = int(step * 100 / total_steps)
        tasks_progress[task_id]["progress"] = progress
        print("Progress : ", progress)

    time.sleep(300)