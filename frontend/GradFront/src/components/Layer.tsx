import {
    Card,
    CardDescription,
    CardHeader,
    CardTitle,
    CardContent
  } from "@/components/ui/card"
import Arrow from './ui/arrow';
import { Button } from "./ui/button";
import { TrashIcon } from "lucide-react";

const Layer = (props: any) => {

    const {
        showArrow,
        layer,
        deletable,
        deleteLayer
    } = props;

    const capitalize = (word: string) => (
        word.charAt(0).toUpperCase() + word.slice(1) 
    );

    return (
        <>
            <Card>
                <CardHeader>
                    <CardTitle>{capitalize(layer.type)}</CardTitle>
                    <CardDescription>{layer.size}</CardDescription>
                </CardHeader>
                {deletable && (
                    <CardContent className="flex justify-center">
                        <Button variant = "destructive" onClick={deleteLayer}><TrashIcon /></Button>
                    </CardContent>
                )}
            </Card>
            {showArrow && <Arrow />}
        </>
    )
};

export default Layer;