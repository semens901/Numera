#ifndef CSVTABLE_H
#define CSVTABLE_H
#include "stats/BasicStats.h"
#include "io/IDataLoader.h"
#include "io/CsvDataLoader.h"

#include <optional>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>

/**
 * @brief A lightweight container for column-oriented CSV-like data.
 *
 * CSVTable stores data as a mapping from keys (e.g. column names)
 * to vectors of values. Each key represents a logical group or column,
 * and the associated vector holds all values belonging to that group.
 *
 * The class provides basic container semantics (iteration, access,
 * insertion, removal) as well as simple descriptive statistics
 * computed over all stored values.
 *
 * This container does not perform any I/O and is intended to be used
 * as an in-memory data representation layer.
 *
 * @tparam key_type   Type used as a key (e.g. std::string for column names)
 * @tparam data_type  Type of stored values (e.g. int, double)
 */

namespace nr
{
    class CSVTable
    {
    public:
        // Basic types
        using cell_type   = std::string;
        using row_type    = std::vector<cell_type>;
        using table_type  = std::vector<row_type>;
        using size_type   = std::size_t;

        CSVTable() : headers(), data(), rows_count(0), cols_count(0) {};
        CSVTable(IDataLoader<std::unordered_map<std::string, std::vector<std::string>>>* loader, std::string filename);
        CSVTable(const CSVTable&) = default;
        CSVTable(CSVTable&&) = default;
        CSVTable& operator=(const CSVTable&) = default;
        CSVTable& operator=(CSVTable&&) = default;
        explicit CSVTable(std::vector<cell_type> headers);
        CSVTable(std::vector<std::string> headers, std::vector<row_type> rows);
        //CSVTable(IDataLoader<std::unordered_map<std::string, std::vector<std::string>>>& loader, std::string filename);
        ~CSVTable() = default;

        /// Number of rows (excluding header)
        size_type row_count() const noexcept;

        /// Number of columns
        size_type column_count() const noexcept;

        /// Check if table is empty
        bool empty() const noexcept;

        /// Access row by index (throws if out of range)
        const row_type row(size_type index) const;

        /// Check if column exists
        bool has_column(const std::string& name) const noexcept;

        /// Get column index by name (throws if not found)
        size_type column_index(const std::string& name) const;

        /// Extract raw string column by index
        std::vector<cell_type> column(size_type index) const;

        /// Extract raw string column by name
        std::vector<cell_type> column(const std::string& name) const;

        /// Extract column and convert to type T (strict)
        template <typename T>
        std::vector<T> extract_column(const std::string& column_name) const;

        template <typename T>
        std::vector<T> extract_row(const CSVTable::size_type& row_index) const;

        /// Add a new row (must match column count)
        void add_row(row_type row);

        /// Clear all data (keeps header)
        void clear();

    private:
        void fill_in_the_blanks();
        
        template <typename T>
        static T string_to(const std::string& s);

        row_type headers;  // column headers
        table_type data;     // table data (rows)
        size_t rows_count;
        size_t cols_count;
    };
    
    template <typename T>
    inline std::vector<T> CSVTable::extract_column(const std::string &column_name) const
    {
        // Extract a column by name and convert each cell to type T.
        // Throws if the column does not exist or conversion fails.
        const auto col = column(column_name);

        std::vector<T> result;
        result.reserve(col.size());

        for (const auto& var : col) {
            result.push_back(string_to<T>(var)); // Convert string → T
        }

        return result;
    }

    template <typename T>
    inline std::vector<T> CSVTable::extract_row(const CSVTable::size_type& row_index) const
    {
        auto row = this->row(row_index);
        std::vector<T> result;
        result.reserve(row.size());
        for (const auto& var : row) {
            result.push_back(string_to<T>(var)); // Convert string → T
        }
        return result;
    }

    template <typename T>
    inline T CSVTable::string_to(const std::string &s)
    {
        static_assert(
        std::is_arithmetic_v<T> ||
        std::is_same_v<T, bool> ||
        std::is_same_v<T, std::string>,
        "CSVTable::string_to<T>: unsupported target type"
        );

         // Strings are returned as-is (no parsing required)
        if constexpr (std::is_same_v<T, std::string>) 
        {
            return s;
        }

        std::istringstream iss(s);
        T value;

        // Special handling for boolean values
        if constexpr (std::is_same_v<T, bool>) 
        {
            std::string tmp;
            iss >> tmp;

            // Normalize to lowercase for robust comparison
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

            // Accept common CSV boolean representations
            if (tmp == "1" || tmp == "true" || tmp == "yes")
                return true;
            if (tmp == "0" || tmp == "false" || tmp == "no")
                return false;

            // Invalid boolean value
            throw std::invalid_argument(
                "CSVTable: invalid boolean value: '" + s + "'"
            );
        } else {
                iss >> value;
                if (iss.fail() || !iss.eof()) {
                    throw std::invalid_argument("Cannot convert string to value: " + s);
                }
            }

        return value;
    }

}

#endif // CSVTABLE_H