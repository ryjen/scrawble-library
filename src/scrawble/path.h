#ifndef SCRAWBLE_PATH_H
#define SCRAWBLE_PATH_H

#import <vector>

namespace scrawble
{
    class word;

    class path
    {
       public:
        typedef char value_type;
        typedef std::vector<value_type> value_list;
        typedef std::shared_ptr<path> ptr;

        static const value_type DELIMITER;
        
        path(const value_type &value);

        path(const value_list &values);

        path(const value_list &value, const path::ptr &other);
        
        path(const path &other);
        
        path(path &&other);
        
        virtual ~path();
        
        path &operator=(const path &other);
        path &operator=(path &&other);

        value_list reverse_prefix_values() const;

        value_list suffix_values() const;

        bool has_delimiter() const;

        std::string to_string() const;

        const value_list &to_array() const;

        bool starts_with(const value_list &values) const;

        word to_word() const;

        bool operator==(const path &other) const;

        bool operator<(const path &other) const;

       private:
        value_list values_;
    };
}

#endif
