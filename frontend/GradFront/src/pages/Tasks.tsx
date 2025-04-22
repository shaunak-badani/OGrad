import BackdropWithSpinner from "@/components/ui/backdropWithSpinner";
import {
    Table,
    TableBody,
    TableHead,
    TableHeader,
    TableRow,
  } from "@/components/ui/table"
import { useEffect, useState } from "react";
import backendClient from "@/utils/backendClient";
import Task from "@/components/task";



const Tasks = () => {
    const [loading, setLoading] = useState(false);
    const [tasks, setTasks] = useState([]);

    useEffect(() => {
      const fetchData = async () => {
        const response = await backendClient.get("/tasks");
        setTasks(response.data);
        setLoading(false);
        return response;
      }
      fetchData();
    }, []);

    if(loading)
    {
      return (
        <BackdropWithSpinner />
      );
    }

    return  (
        <div>
            <Table>
                <TableHeader>
                    <TableRow>
                    <TableHead className="text-center w-1/3">Task Id</TableHead>
                    <TableHead className="text-center w-1/3">Process Id</TableHead>
                    <TableHead className="text-center w-1/3">Progress</TableHead>
                    </TableRow>
                </TableHeader>
                <TableBody>
                    {tasks.map((task) => (
                      <Task 
                        key = {task["task_id"]}
                        task = {task}
                      />
                    ))}
                </TableBody>
            </Table>
        </div>
    );
};

export default Tasks;