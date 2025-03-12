import {
    TableCell,
    TableRow,
} from "@/components/ui/table"
import { Progress } from "@/components/ui/progress"
import { useEffect, useState } from "react";
import backendClient from "@/utils/backendClient";

const Task = (props: any) => {
    const { task } = props;
    const [progress, setProgress] = useState(task["progress"]);

    useEffect(() => {
        if(progress === 1.0)
            return;

        const fetchData = async (interval: any) => {
          const response = await backendClient.get(`/task-progress/${task["task_id"]}`);
          const currentProgress = response.data.progress;
          setProgress(currentProgress);
          if(currentProgress === 1.0)
            clearInterval(interval);
        }
        const interval = setInterval(() => fetchData(interval), 5000);

        return () => {
            clearInterval(interval);
        }
      }, []);
    
    return (
        <TableRow>
            <TableCell className="font-medium">{task["task_id"]}</TableCell>
            <TableCell>{task["pid"]}</TableCell>
            <TableCell><Progress value={progress * 100} /></TableCell>
        </TableRow>
    );
}

export default Task