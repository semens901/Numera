#include "CSVTable.h"

nr::CSVTable::CSVTable(IDataLoader<std::unordered_map<std::string, std::vector<std::string>>>* loader, std::string filename)
{
    CSVDataLoader* csv_loader = dynamic_cast<CSVDataLoader*>(loader);
    if (!csv_loader) {
        throw std::invalid_argument("CSVTable constructor: loader must be a CSVDataLoader");
    }
    auto loaded_data = csv_loader->load(filename);
    headers = csv_loader->get_column_order();
    // initialize counts
    cols_count = headers.size();

    size_t n_rows = 0;
    if (!headers.empty()) {
        // ensure first header exists in loaded data
        auto it0 = loaded_data.find(headers[0]);
        if (it0 == loaded_data.end())
            throw std::invalid_argument("CSVTable: header not found in loaded data: " + headers[0]);
        n_rows = it0->second.size();

        // Validate all headers exist and have consistent sizes
        for (const auto &h : headers) {
            auto it = loaded_data.find(h);
            if (it == loaded_data.end())
                throw std::invalid_argument("CSVTable: header not found in loaded data: " + h);
            if (it->second.size() != n_rows)
                throw std::invalid_argument("CSVTable: column sizes are inconsistent for header: " + h);
        }
    }

    rows_count = n_rows;

    for (size_t i = 0; i < n_rows; ++i)
    {
        row_type row;
        row.reserve(cols_count);
        for (const auto& header : headers)
        {
            // safe to use at() because we validated sizes above
            row.push_back(loaded_data.at(header)[i]);
        }
        data.push_back(std::move(row));
    }

    fill_in_the_blanks();
}

nr::CSVTable::CSVTable(std::vector<cell_type> headers) : headers(std::move(headers)), cols_count(this->headers.size()), rows_count(0) {}

nr::CSVTable::CSVTable(std::vector<std::string> headers, std::vector<row_type> rows)
{
    this->headers = std::move(headers);
    this->data = std::move(rows);
    cols_count = this->headers.size();
    rows_count = this->data.size();
    fill_in_the_blanks();
}

nr::CSVTable::size_type nr::CSVTable::row_count() const noexcept
{
    return data.size();
}

nr::CSVTable::size_type nr::CSVTable::column_count() const noexcept
{
    return headers.size();
}

bool nr::CSVTable::empty() const noexcept
{
    return data.empty();
}

const nr::CSVTable::row_type nr::CSVTable::row(size_type index) const
{
    // TODO: insert return statement here
    nr::CSVTable::row_type result;
    if (index >= rows_count)
          throw std::out_of_range("row: index out of range");
    
    for (const auto &col : this->data) 
    {
        result.push_back(col[index]);
    }

    return result;
}

bool nr::CSVTable::has_column(const std::string &name) const noexcept
{
    return std::find(headers.begin(), headers.end(), name) != headers.end();
}

nr::CSVTable::size_type nr::CSVTable::column_index(const std::string &name) const
{
    auto it = std::find(headers.begin(), headers.end(), name);
    if (it == headers.end())
        throw std::out_of_range("column_index: column not found: " + name);
    return static_cast<size_type>(std::distance(headers.begin(), it));
}

std::vector<nr::CSVTable::cell_type> nr::CSVTable::column(size_type index) const
{
    if (index >= cols_count) throw std::out_of_range("column: index out of range");

    std::vector<cell_type> result;
    result.reserve(data.size());
    for (size_t i = 0; i < data.size(); ++i)
    {
        // use at() to get checked access into row
        result.push_back(data[i].at(index));
    }

    return result;
}

std::vector<nr::CSVTable::cell_type> nr::CSVTable::column(const std::string &name) const
{
    size_type index = column_index(name);
    return column(index);
}

void nr::CSVTable::add_row(row_type row)
{
    if (headers.empty()) {
        throw std::invalid_argument("Cannot add row: headers not defined");
    }

    if (row.size() != cols_count)
    {
        throw std::invalid_argument("Row size does not match number of columns");
    }
    data.push_back(std::move(row));
    ++rows_count;
}

void nr::CSVTable::clear()
{
    data.clear();
    headers.clear();
    rows_count = 0;
    cols_count = 0;
}

void nr::CSVTable::fill_in_the_blanks()
{
    /*
        Ensures all rows have the same number of columns by filling
        missing cells with empty strings.
    */
    for (auto& row : data)
    {
        while (row.size() < cols_count)
        {
            row.push_back("");
        }
    }
}
