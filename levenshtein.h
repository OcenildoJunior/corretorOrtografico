#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <algorithm>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

inline std::wstring string_to_wstring(const std::string& input)
{
    try {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(input);
    } catch(std::range_error& e) {
        size_t length = input.length();
        std::wstring result;
        result.reserve(length);
        for(size_t i = 0; i < length; i++)
        {
            result.push_back(input[i] & 0xFF);
        }
        return result;
    }
}


template<typename T>
typename T::size_type levenshtein(const T &source,
        const T &target,
        typename T::size_type insert_cost = 1,
        typename T::size_type delete_cost = 1,
        typename T::size_type replace_cost = 1
        ) {


    auto wSource = string_to_wstring(source);
    auto wTarget = string_to_wstring(target);

    if (wSource.size() > wTarget.size()) {
        return levenshtein(target, source, delete_cost, insert_cost, replace_cost);
    }

    using TSizeType = typename T::size_type;
    const TSizeType min_size = wSource.size(), max_size = wTarget.size();
    std::vector<TSizeType> lev_dist(min_size + 1);

    lev_dist[0] = 0;
    for (TSizeType i = 1; i <= min_size; ++i) {
        lev_dist[i] = lev_dist[i - 1] + delete_cost;
    }

    for (TSizeType j = 1; j <= max_size; ++j) {
        TSizeType previous_diagonal = lev_dist[0], previous_diagonal_save;
        lev_dist[0] += insert_cost;

        auto t = static_cast<int>(wTarget[j - 1]);
        for (TSizeType i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            auto s = static_cast<int>(wSource[i - 1]);
            if (t == s) {
                lev_dist[i] = previous_diagonal;
            } else {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1] + delete_cost, lev_dist[i] + insert_cost), previous_diagonal + replace_cost);
            }
            previous_diagonal = previous_diagonal_save;
        }
    }

    return lev_dist[min_size];
}

#endif
