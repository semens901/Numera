#ifndef IDATALOADER_H
#define IDATALOADER_H
#include<vector>
#include<string>

template<typename Container>
class IDataLoader {
public:
    virtual ~IDataLoader() = default; 

    virtual Container load(const std::string& filename) = 0;
    
    virtual void save(const std::string& filename, const std::vector<double>& data) const = 0;
};

#endif // IDATALOADER_H