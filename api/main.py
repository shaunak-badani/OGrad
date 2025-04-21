from fastapi import FastAPI, BackgroundTasks, HTTPException, status
from fastapi.middleware.cors import CORSMiddleware
from contextlib import asynccontextmanager
from pydantic import BaseModel
import uuid
from typing import Dict, Any
import time
import subprocess
from db import DBHelper
from MLJobConfig import MLJobConfig
import os
from utils import Utils

class Task(BaseModel):
    task_id: str
    pid: int
    progress: float

class TaskProgress(BaseModel):
    progress: float

@asynccontextmanager
async def lifespan(app: FastAPI):
    DBHelper.initialize_database()
    yield  

app = FastAPI(lifespan = lifespan)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:5173"],  # React dev server
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.post("/start_task")
async def start_task(data: Dict[Any, Any], background_tasks: BackgroundTasks):
    """Start a new task and return its ID"""
    try:
        if "job" not in data:
            raise RuntimeError("No job to be done! Please check your request and try again.")
        MLJobConfig.validate(data["job"])
    except RuntimeError as e:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail = e.__str__()
        )
    jobConfig = data["job"]
    task_id = str(uuid.uuid4())
    Utils.prepare_job(task_id, jobConfig)
    
    background_tasks.add_task(Utils.process_task, task_id, jobConfig["num_epochs"])
    return { "message" : "success" }

@app.get("/tasks")
def get_all_tasks() -> list[Task]:
    tasks_results = DBHelper.execute_query("SELECT * FROM jobs")
    all_tasks = []
    for task in tasks_results:
        task_id, pid, num_steps = task
        steps_so_far = Utils.get_progress_so_far(task_id)
        progress = float(steps_so_far) / num_steps
        all_tasks.append(Task(pid = pid, task_id = task_id, progress = progress))
    return all_tasks


@app.get("/task-progress/{task_id}")
def get_task_progress(task_id: str):
    tasks_results = DBHelper.execute_query("SELECT totalSteps FROM jobs WHERE taskid = ?", (task_id,))
    total_steps = tasks_results[0][0]
    steps_so_far = Utils.get_progress_so_far(task_id)
    return TaskProgress(progress = float(steps_so_far) / total_steps)