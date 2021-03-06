#ifndef teca_program_options_h
#define teca_program_options_h

#include "teca_config.h"

#if defined(TECA_HAS_BOOST)
namespace boost
{
    namespace program_options
    {
        class options_description;
        class variables_map;
    }
};

using options_description
    = boost::program_options::options_description;

using variables_map
    = boost::program_options::variables_map;

// initialize the given options description
// with algorithm's properties
#define TECA_GET_ALGORITHM_PROPERTIES_DESCRIPTION() \
    void get_properties_description(                \
        const std::string &prefix,                  \
        options_description &opts) override;        \

// initialize the algorithm from the given options
// variable map.
#define TECA_SET_ALGORITHM_PROPERTIES()             \
    void set_properties(                            \
        const std::string &prefix,                  \
        variables_map &opts) override;              \

// helpers for implementation dealing with Boost
// program options

#define TECA_POPTS_GET(_type, _prefix, _name, _desc)    \
     ((_prefix + #_name).c_str(), boost::program_options::value<_type>(), _desc)

#define TECA_POPTS_SET(_opts, _type, _prefix, _name)            \
    {string opt_name = _prefix + #_name;                        \
    if (_opts.count(opt_name))                                  \
    {                                                           \
        this->set_##_name(_opts[opt_name].as<_type>());         \
    }}

#else

#define TECA_GET_ALGORITHM_PROPERTIES_DESCRIPTION()
#define TECA_SET_ALGORITHM_PROPERTIES()

#endif

#endif
