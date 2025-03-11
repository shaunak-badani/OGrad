from flask import Flask, request, Response, jsonify
import logging
from .MLJobConfig import MLJobConfig
import json
from pathlib import Path

app = Flask(__name__)
logging.basicConfig(filename = 'logs/all-logs.log')

@app.route('/runML', methods = ["POST"])
def receive_job_request():
    try:
        if "job" not in request.json:
            raise RuntimeError("No job to be done! Please check your request and try again.")
        MLJobConfig.validate(request.json["job"])
    except RuntimeError as e:
        return jsonify(error = e.__str__()), 400

    job_json = request.json["job"]
    job_id = MLJobConfig.add_metadata_for_job(job_json)
    p = Path('./jobs')
    q = p / job_id
    q.mkdir(exist_ok=True)

    with open(q / 'params.json', 'w') as f:
        json.dump(job_json, f)
    return jsonify(message = "ok"), 200

@app.errorhandler(405)
def method_not_allowed(e):
    return jsonify(error = "Request method disallowed on the api. Please check your request and try again!"), 405