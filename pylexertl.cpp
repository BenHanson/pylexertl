#include "../lexertl17/include/lexertl/debug.hpp"
#include "../lexertl17/include/lexertl/generator.hpp"
#include "../lexertl17/include/lexertl/lookup.hpp"
#include "../lexertl17/include/lexertl/match_results.hpp"
#include "../lexertl17/include/lexertl/utf_iterators.hpp"

#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

#ifdef WIN32
using lex_char = char32_t;
using lex_debug = lexertl::u32debug;
using lex_generator = lexertl::u32generator;
using lex_match = lexertl::u32cmatch;
using lex_oss = std::basic_ostringstream<lex_char>;
using lex_rules = lexertl::u32rules;
using lex_sm = lexertl::u32state_machine;
using lex_stream = std::basic_ostringstream<lex_char>;
using lex_string = std::u32string;
#else
using lex_char = wchar_t;
using lex_debug = lexertl::wdebug;
using lex_generator = lexertl::wgenerator;
using lex_match = lexertl::wcmatch;
using lex_oss = std::wostringstream;
using lex_rules = lexertl::wrules;
using lex_sm = lexertl::wstate_machine;
using lex_stream = std::wostringstream;
using lex_string = std::wstring;
#endif

using utf8_in_iterator = lexertl::basic_utf8_in_iterator<const char*, lex_char>;
using utf8_out_iterator = lexertl::basic_utf8_out_iterator<const lex_char*>;

struct rules : lex_rules
{
    rules() :
        lex_rules()
    {
    }

    rules(const std::size_t flags_) :
        lex_rules(flags_)
    {
    }

    const char* state(const uint16_t index_) const
    {
        const lex_char* name_ = lex_rules::state(index_);
        const lex_char* end_name_ = name_;
        static std::string ret_;

        while (*end_name_)
            ++end_name_;

        ret_.assign(utf8_out_iterator(name_, end_name_),
            utf8_out_iterator(end_name_, end_name_));
        return ret_.c_str();
    }

    uint16_t state(const char* name_) const
    {
        const char* end_name_ = name_ + strlen(name_);
        lex_string nm_(utf8_in_iterator(name_, end_name_),
            utf8_in_iterator(end_name_, end_name_));

        return lex_rules::state(nm_.c_str());
    }

    id_type push_state(const char* name_)
    {
        const char* end_name_ = name_ + strlen(name_);
        lex_string nm_(utf8_in_iterator(name_, end_name_),
            utf8_in_iterator(end_name_, end_name_));

        return lex_rules::push_state(nm_.c_str());
    }

    void insert_macro(const char* name_, const char* regex_)
    {
        const char* end_name_ = name_ + strlen(name_);
        const char* end_regex_ = regex_ + strlen(regex_);
        lex_string nm_(utf8_in_iterator(name_, end_name_),
            utf8_in_iterator(end_name_, end_name_));
        lex_string rx_(utf8_in_iterator(regex_, end_regex_),
            utf8_in_iterator(end_regex_, end_regex_));

        lex_rules::insert_macro(nm_.c_str(), rx_.c_str());
    }

    void push(const char* regex_, const uint16_t id_)
    {
        const char* end_rx_ = regex_ + strlen(regex_);
        lex_string rx_(utf8_in_iterator(regex_, end_rx_),
            utf8_in_iterator(end_rx_, end_rx_));

        lex_rules::push(rx_, id_);
    }

    void push(const char* regex_, const uint16_t id_, const uint16_t user_id_)
    {
        const char* end_regex_ = regex_ + strlen(regex_);
        lex_string rx_(utf8_in_iterator(regex_, end_regex_),
            utf8_in_iterator(end_regex_, end_regex_));

        lex_rules::push(rx_, id_, user_id_);
    }

    void push(const char* curr_dfa_, const char* regex_, const char* new_dfa_)
    {
        const char* end_curr_dfa_ = curr_dfa_ + strlen(curr_dfa_);
        const char* end_regex_ = regex_ + strlen(regex_);
        const char* end_new_dfa_ = new_dfa_ + strlen(new_dfa_);
        lex_string curr_(utf8_in_iterator(curr_dfa_, end_curr_dfa_),
            utf8_in_iterator(end_curr_dfa_, end_curr_dfa_));
        lex_string rx_(utf8_in_iterator(regex_, end_regex_),
            utf8_in_iterator(end_regex_, end_regex_));
        lex_string new_(utf8_in_iterator(new_dfa_, end_new_dfa_),
            utf8_in_iterator(end_new_dfa_, end_new_dfa_));

        lex_rules::push(curr_.c_str(), rx_.c_str(), new_.c_str());
    }

    void push(const char* curr_dfa_, const char* regex_, const id_type id_,
        const char* new_dfa_)
    {
        const char* end_curr_dfa_ = curr_dfa_ + strlen(curr_dfa_);
        const char* end_regex_ = regex_ + strlen(regex_);
        const char* end_new_dfa_ = new_dfa_ + strlen(new_dfa_);
        lex_string curr_(utf8_in_iterator(curr_dfa_, end_curr_dfa_),
            utf8_in_iterator(end_curr_dfa_, end_curr_dfa_));
        lex_string rx_(utf8_in_iterator(regex_, end_regex_),
            utf8_in_iterator(end_regex_, end_regex_));
        lex_string new_(utf8_in_iterator(new_dfa_, end_new_dfa_),
            utf8_in_iterator(end_new_dfa_, end_new_dfa_));

        lex_rules::push(curr_.c_str(), rx_.c_str(), id_, new_.c_str());
    }

    void push(const char* curr_dfa_, const char* regex_, const id_type id_,
        const char* new_dfa_, const uint16_t user_id_)
    {
        const char* end_curr_dfa_ = curr_dfa_ + strlen(curr_dfa_);
        const char* end_regex_ = regex_ + strlen(regex_);
        const char* end_new_dfa_ = new_dfa_ + strlen(new_dfa_);
        lex_string curr_(utf8_in_iterator(curr_dfa_, end_curr_dfa_),
            utf8_in_iterator(end_curr_dfa_, end_curr_dfa_));
        lex_string rx_(utf8_in_iterator(regex_, end_regex_),
            utf8_in_iterator(end_regex_, end_regex_));
        lex_string new_(utf8_in_iterator(new_dfa_, end_new_dfa_),
            utf8_in_iterator(end_new_dfa_, end_new_dfa_));

        lex_rules::push(curr_.c_str(), rx_.c_str(), id_, new_.c_str(),
            user_id_);
    }
};

struct match_results : lex_match
{
    lex_string _input;

    match_results(const char* input_) :
        lex_match()
    {
        // Base classes are initialised first
        // so initialise via reset() to allow _input to be set
        reset(input_);
    }

    void reset(const char* input_)
    {
        _input.assign(utf8_in_iterator(input_, input_ + strlen(input_)),
            utf8_in_iterator(input_ + strlen(input_), input_ + strlen(input_)));
        lex_match::reset(_input.c_str(), _input.c_str() + _input.size());
    }

    std::string str() const
    {
        std::string ret_(utf8_out_iterator(first, second),
            utf8_out_iterator(second, second));

        return ret_;
    }
};

void build(const rules& rules_, lex_sm& sm_)
{
    lex_generator::build(rules_, sm_);
}

void lookup(const lex_sm& sm_, match_results& results_)
{
    lexertl::lookup(sm_, results_);
}

void dump(const lex_sm& sm_)
{
    lex_oss ss_;
    lex_string ret_;

    lex_debug::dump(sm_, ss_);
    ret_ = ss_.str();
    std::cout << std::string(utf8_out_iterator(ret_.c_str(), ret_.c_str() + ret_.size()),
        utf8_out_iterator(ret_.c_str() + ret_.size(), ret_.c_str() + ret_.size()));
}

PYBIND11_MODULE(pylexertl, m)
{
    py::class_<rules>
        (m, "rules")
        .def(py::init<>())
        .def(py::init<const std::size_t>())
        .def("clear",
            static_cast<void(lex_rules::*) ()>(&lex_rules::clear))
        .def("clear",
            static_cast<void(lex_rules::*) (const uint16_t)>
            (&lex_rules::clear))
        .def("flags",
            static_cast<void(lex_rules::*) (const std::size_t)>
            (&lex_rules::flags))
        .def("flags",
            static_cast<std::size_t(lex_rules::*) () const>
            (&lex_rules::flags))
        .def_static("skip", &lex_rules::skip)
        .def_static("eoi", &lex_rules::skip)
        .def_static("npos", &lex_rules::skip)
        .def("state",
            static_cast<const char* (rules::*)(const uint16_t) const>
            (&rules::state))
        .def("state",
            static_cast<uint16_t (rules::*)(const char*) const>
            (&rules::state))
        .def("push_state",
            static_cast<uint16_t (rules::*)(const char*)>
            (&rules::push_state))
        .def("insert_macro",
            static_cast<void (rules::*)(const char*, const char*)>
            (&rules::insert_macro))
        .def("push",
            static_cast<void (rules::*)(const char*, const uint16_t)>
            (&rules::push))
        .def("push",
            static_cast<void (rules::*)(const char*, const char*, const char*)>
            (&rules::push))
        .def("push",
            static_cast<void (rules::*)(const char*, const char*,
                const uint16_t, const char*)>
            (&rules::push))
        .def("push",
            static_cast<void (rules::*)(const char*, const char*,
                const uint16_t, const char*, const uint16_t)>
            (&rules::push))
        .def("reverse",
            static_cast<void(lex_rules::*) ()>
            (&lex_rules::reverse))
        .def("empty",
            static_cast<bool(lex_rules::*) () const>
            (&lex_rules::empty));

    py::class_<lex_sm>(m, "state_machine")
        .def(py::init<>());

    py::class_<match_results>(m, "match_results")
        .def(py::init<const char*>())
        .def("reset", &match_results::reset)
        .def_readwrite("id", &match_results::id)
        .def_readwrite("user_id", &match_results::user_id)
        .def("str", &match_results::str)
        .def_readwrite("bol", &match_results::bol)
        .def_readwrite("state", &match_results::state);

    m.def("build", &build);
    m.def("lookup", &lookup);
    m.def("dump", &dump);
}
