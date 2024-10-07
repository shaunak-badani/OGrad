import os
import numpy as np
import json

class Model:
    
    def __init__(self, model_name):
        self.model_path = os.path.join("../", model_name)
        if not os.path.isdir(self.model_path):
            raise Exception("Directory "+ self.model_path + " does not exist!")
        json_path = os.path.join(self.model_path, "out.json")
        if not os.path.exists(json_path):
            raise Exception("json file not found!")
        self.json = json.load(open(json_path))
        self.layers = []


    def load_model(self):
        for idx, layer in enumerate(self.json.get('layers')):
            if layer.get('type') == 'linear':
                layer_shape = (layer.get('input_size'), layer.get('output_size'))
                layer_weights = np.loadtxt(os.path.join(self.model_path, "model", str(idx) + ".csv"), delimiter = ',', ndmin = 2)
                if layer_weights.shape != layer_shape:
                    raise Exception("Mismatch between expected shape: ", layer_shape, " and obtained shape: ", layer_weights.shape)

                self.layers.append( {'w' : layer_weights })

    def __call__(self, x):

        y = x[:]
        for layer in self.layers:
            y = x @ layer.get('w')
        return y
