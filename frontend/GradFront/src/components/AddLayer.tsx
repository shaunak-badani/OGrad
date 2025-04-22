import {
    Card,
    CardTitle,
    CardHeader,
    CardDescription,
    CardFooter,
    CardContent
} from "@/components/ui/card"
import {
    Select,
    SelectContent,
    SelectItem,
    SelectTrigger,
    SelectValue,
} from "@/components/ui/select"
import { Input } from "@/components/ui/input"
import { Label } from "@/components/ui/label"
import { Button } from './ui/button'
import { useState } from "react"

const AddLayer = (props: any) => {

    const { addLayer, finalOutputSize } = props; 
    console.log("Final output size: ", finalOutputSize);

    const [inputSize, setInputSize] = useState<number | null>(finalOutputSize);
    const [outputSize, setOutputSize] = useState<number | null>(null);
    const [layerType, setLayerType] = useState("linear");


    const handleAddLayer = () => {
        let layer = {
            "type": layerType,
            "input_size": inputSize,
            "output_size": outputSize
        }
        addLayer(layer);
    };

    const changeInputSize = (event: any) => {
        if(event.target.value)
            setInputSize(Number(event.target.value));
        else
            setInputSize(null);
    }

    const changeOutputSize = (event: any) => {
        if(event.target.value)
            setOutputSize(Number(event.target.value));
        else
            setOutputSize(null);
    }

    return (
        <Card className="w-[350px] mx-auto">
            <CardHeader>
                <CardTitle>Add Layer</CardTitle>
                <CardDescription>Select the new type of layer to be added.</CardDescription>
            </CardHeader>
            <CardContent>
                <form id="layer_form" >
                <div className="grid w-full items-center gap-4">
                    <div className="flex flex-col space-y-1.5">
                    <Label htmlFor="type">Layer Type</Label>
                    <Select value={layerType} onValueChange={(value) => setLayerType(value)} >
                        <SelectTrigger id="type">
                        <SelectValue placeholder="Select" />
                        </SelectTrigger>
                        <SelectContent position="popper">
                        <SelectItem value="linear">Linear</SelectItem>
                        </SelectContent>
                    </Select>
                    </div>
                    <div className="flex flex-col space-y-1.5">
                    <Label htmlFor="input_size">Input Size</Label>
                    <Input  
                        id="input_size"
                        readOnly={finalOutputSize !== null}
                        disabled={finalOutputSize !== null}
                        onChange={changeInputSize}
                        placeholder="Input size, e.g. 512"
                        value={inputSize ?? ''}
                        type="number" />
                    </div>
                    <div className="flex flex-col space-y-1.5">
                    <Label htmlFor="output_size" >Output Size</Label>
                    <Input 
                        id="output_size" 
                            onChange={changeOutputSize}
                            value={outputSize ?? ''}
                            placeholder="Output size, e.g. 11" 
                            type="number" />
                    </div>
                </div>
                </form>
            </CardContent>
            <CardFooter className="flex justify-center">
                <Button onClick={handleAddLayer}>Add</Button>
            </CardFooter>
            </Card>
    );
};

export default AddLayer;