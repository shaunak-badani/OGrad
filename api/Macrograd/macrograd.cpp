#include "CSVReader.h"
#include "DataSetReader.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>
#include "model_mediator.h"

int main(int argc, char* argv[])
{

    if(argc != 2)
    {
        std::cout << "Usage : macrograd <path_to_json_file>" << std::endl;
        return 1;
    }

    std::filesystem::path filePath = argv[1];
    if(!std::filesystem::exists(filePath))
    {
        std::cout << "Couldn't find file " << argv[1]  << std::endl;
        return 1;
    }

    std::ifstream fileStream(argv[1]);
    nlohmann::json data;
    try {
        data = nlohmann::json::parse(fileStream);
    }
    catch(nlohmann::json_abi_v3_11_3::detail::parse_error error)
    {
        std::cout << "Couldn't parse JSON in file passed." << std::endl;
        std::cout << error.what() << std::endl;
        return 1;
    }
    ModelMediator modelMediator = data.template get<ModelMediator>();
    modelMediator.setJson(data);
    modelMediator.run();
    modelMediator.summarize();
    return 0;
}