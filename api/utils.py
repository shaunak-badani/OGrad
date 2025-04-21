import subprocess
from db import DBHelper
import os
from pathlib import Path
from typing import Dict, Any
import json
import pandas as pd

class Utils:
    """
    Miscellaneous class to help out with various tasks
    """

    @staticmethod
    def process_task(task_id: str, numSteps: int):
        """Background task to submit ML job"""
        jsonFilePath = os.fspath(Path("out_models") / task_id / (task_id + ".json"))
        print(jsonFilePath)
        process = subprocess.Popen(['build/Macrograd', jsonFilePath], cwd = "./Macrograd", stdout=subprocess.PIPE)
        process_id = process.pid
        print("Number of steps: ", numSteps)
        DBHelper.execute_query("INSERT INTO jobs VALUES(?, ?, ?)", (task_id, process_id, numSteps))

    
    @staticmethod
    def prepare_job(task_id: str, jsonConfig: Dict[Any, Any]):
        """Creates directories and prepares the job for submission"""
        base_dir = Path('./Macrograd/out_models')
        job_dir = base_dir / task_id
        job_dir.mkdir(exist_ok=True)

        # Changing path of out_models
        jsonConfig["output_folder"] = os.fspath(Path("out_models") / task_id)


        jsonFileName = task_id + ".json"
        jsonConfigPath = job_dir / jsonFileName
        with open(jsonConfigPath, "w") as jsonFile:
            json.dump(jsonConfig, jsonFile, indent = 4)

    @staticmethod
    def get_progress_so_far(task_id: str):
        """Returns number of steps completed in the job"""
        scalar_path = os.fspath(Path("./Macrograd/out_models") / task_id / "scalars.csv")
        if not os.path.exists(scalar_path):
            return 0
        df = pd.read_csv(scalar_path, names = ["epoch_no", "loss"])
        if df.shape[0] == 0:
            return 0
        return df["epoch_no"].iloc[-1]
        



