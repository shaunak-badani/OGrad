import backendClient from '@/utils/backendClient';
import { Button } from './ui/button'
import { useState, useRef } from 'react';
import Layers from './Layers';
import AddLayer from './AddLayer';



const JobConfig = (props) => {

    const [job, setJob] = useState({
        "num_epochs": 10000,
        "layers":[
            {
                "type": "linear",
                "input_size": 11,
                "output_size": 512
            },
            {
                "type": "linear",
                "input_size": 512,
                "output_size": 1
            }
        ],
        "learning_rate": {
            "type": "simple",
            "value": 0.01
        },
        "loss_fn": "root_mean_squared",
        "dataset_reader": "csv_reader",
        "dataset" : "monk/train.csv",
        "batch_size": 1000
    });

    let finalOutputSize = null;
    if(job["layers"].length){
        var N = job["layers"].length;
        finalOutputSize = job["layers"][N - 1]["output_size"]
    }

    const jobSubmitHandler = async () => {
        const jobConfig = { "job" : job };
        const response =  await backendClient.post("/start_task", jobConfig);
        console.log(response.json())
    }
    const [seed, setSeed] = useState(1);
    const reset = () => {
        setSeed(Math.random());
    }

    const updateKey = (key: string, newValue: any) => {
        setJob(prevJob => {
            let newJob = {
                ...prevJob,
                key: newValue
            };
            return newJob
        });
    }

    

    const deleteLayer = () => {
        console.log("Deleting layer");
        let newLayers = job["layers"];
        newLayers.pop();
        reset();
        updateKey("layers", newLayers);
    }

    const addLayer = (layer: any) => {
        let newLayers = job["layers"];
        newLayers.push(layer);
        reset();
        updateKey("layers", newLayers);
    }


    return (
        <>
        <Layers 
            layers = {job["layers"]}
            deleteLayer={deleteLayer}
        />
        <AddLayer 
            key={seed}
            addLayer={addLayer}
            finalOutputSize={finalOutputSize}
            />
        <Button className="m-8 sm:m-8" onClick={jobSubmitHandler}>Submit job</Button>
        </>
    );
}

export default JobConfig;