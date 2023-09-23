#include <fstream>
#include <iostream>
#include "JsonFileLoader.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"

JsonFileLoader::JsonFileLoader()
{
    std::cout << "---- schema file read ----" << std::endl;
    std::ifstream schema_ifs("schema.json");
    rapidjson::IStreamWrapper schema_isw(schema_ifs);
    std::cout << "---- schema file parse ----" << std::endl;
    rapidjson::Document schema_doc;
    schema_doc.ParseStream(schema_isw);
    rapidjson::SchemaDocument schema(schema_doc);
    rapidjson::SchemaValidator validator(schema);

    std::cout << "---- json file read ----" << std::endl;
    std::ifstream ifs("pet.json");
    rapidjson::IStreamWrapper isw(ifs);
    std::cout << "---- json file parse ----" << std::endl;
    rapidjson::Document doc;
    doc.ParseStream(isw);

    std::cout << "---- json validator ----" << std::endl;
    if (!doc.Accept(validator)) {
        rapidjson::StringBuffer sb;
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
        std::cout << "Invalid schema:" << sb.GetString() << std::endl;
        std::cout << "Invalid keyword:" << validator.GetInvalidSchemaKeyword() << std::endl;
    }
}