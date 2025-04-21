import secrets

class MLJobConfig:

    KEY_CHECK_LIST = [
        ("num_epochs", "Number of steps not provided!"),
        ("layers", "Layers list not provided!"),
        ("learning_rate", "Learning rate not provided!"),
        ("loss_fn", "Loss fn not provided!"),
        ("batch_size", "Batch size not provided!"),
    ]

    @staticmethod
    def check_key(json, key, error_message):
        if key not in json:
            raise RuntimeError(error_message)
        

    @staticmethod
    def validate(json):
        if type(json) is not dict:
            raise RuntimeError("JSON not a dictionary!")
        
        for key, error_message in MLJobConfig.KEY_CHECK_LIST:
            MLJobConfig.check_key(json, key, error_message)

    @staticmethod
    def add_metadata_for_job(json):
        job_id = secrets.token_urlsafe(16)
        json["dataset_reader"] = "csv_reader"
        json["output_folder"] = "."

        return job_id
