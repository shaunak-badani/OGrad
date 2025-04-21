import Layer from "./Layer";

const Layers = (props) => {

    const { layers } = props;
    if(layers.length == 0)
        return (
            <div className='flex justify-center m:6 sm:m-6'>
                Nothing to do here!
            </div>
        );

    let layerTypes = [{
        "type": "Input",
        "size": layers[0]["input_size"]
    }];

    for(var i = 0 ; i < layers.length ; i++)
    {
        layerTypes.push({
            "type": layers[i].type,
            "size": layers[i].output_size
        })
    }

    var N = layerTypes.length;

    return (
        <div className='flex justify-center m:6 sm:m-6'>
            {layerTypes.map((layer, index) => (
                <Layer 
                    showArrow={index < (N - 1)} 
                    layer={layer}
                    deletable={index == (N - 1)}
                    deleteLayer={props.deleteLayer}
                    addLayer={props.addLayer}
                    />
            ))}
        </div>
    );
}

export default Layers;