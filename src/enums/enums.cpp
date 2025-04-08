#include "enums.h"

#include <vector>

std::tuple<Napi::Object, Napi::Object> processEnum(Napi::Env env, std::map<std::string, int> enums)
{
    std::map<int, std::vector<std::string>> revs;

    auto result_str_to_num = Napi::Object::New(env);
    auto result_num_to_str = Napi::Object::New(env);

    for (const auto& [key, value] : enums) {
        result_str_to_num[value] = value;
        if (key.starts_with("First") || key.starts_with("Last")) {
            continue;
        }
        revs[value].push_back(key);
    }

    for (const auto& [key, value] : revs) {
        if (value.size() == 1) {
            result_num_to_str[key] = value[0];
        }
        else {
            auto arr = Napi::Array::New(env, value.size());
            for (uint32_t i = 0; i < value.size(); i++) {
                arr[i] = value[i];
            }
            result_num_to_str[key] = arr;
        }
    }

    return { result_str_to_num, result_num_to_str };
}
