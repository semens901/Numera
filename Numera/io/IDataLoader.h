#ifndef IDATALOADER_H
#define IDATALOADER_H

#include<vector>
#include<string>


template<typename Container>
struct IDataLoader {
    /*
        An abstract parent class, 
        essentially an interface for classes that work with files.
    */
    virtual ~IDataLoader() = default; 

    virtual Container load(const std::string& filename) = 0;
    
    virtual void save(const std::string& filename, const Container& data) const = 0;

};

#endif // IDATALOADER_H