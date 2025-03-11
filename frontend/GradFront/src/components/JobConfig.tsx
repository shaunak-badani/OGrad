import { Button } from './ui/button'
import axios from 'axios';

const JobConfig = (props) => {

    
    const jobSubmitHandler = async () => {
        const response =  await axios.post("http://localhost:8000/start_task");
        console.log(response)
    }


    return (
        <Button className="w-xl" onClick={jobSubmitHandler}>Submit job</Button>
    );
}

export default JobConfig;