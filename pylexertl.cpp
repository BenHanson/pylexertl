#include "../lexertl17/include/lexertl/debug.hpp"
#include "../lexertl17/include/lexertl/generator.hpp"
#include "../lexertl17/include/lexertl/lookup.hpp"
#include "../lexertl17/include/lexertl/match_results.hpp"
#include <pybind11/pybind11.h>
#include "../lexertl17/include/lexertl/utf_iterators.hpp"

namespace py = pybind11;

#ifdef WIN32
using lex_debug = lexertl::u32debug;
using lex_generator = lexertl::u32generator;
using lex_match = lexertl::u32cmatch;
using lex_oss = std::basic_ostringstream<char32_t>;
using lex_rules = lexertl::u32rules;
using lex_sm = lexertl::u32state_machine;
using lex_stream = std::basic_ostringstream<char32_t>;
using lex_string = std::u32string;
using utf8_in_iterator = lexertl::basic_utf8_in_iterator<const char*, char32_t>;
using utf8_out_iterator = lexertl::basic_utf8_out_iterator<const char32_t*>;
#else
using lex_debug = lexertl::wdebug;
using lex_generator = lexertl::wgenerator;
using lex_match = lexertl::wcmatch;
using lex_oss = std::wostringstream;
using lex_rules = lexertl::wrules;
using lex_sm = lexertl::wstate_machine;
using lex_stream = std::wostringstream;
using lex_string = std::wstring;
using utf8_in_iterator = lexertl::basic_utf8_in_iterator<const char*, wchar_t>;
using utf8_out_iterator = lexertl::basic_utf8_out_iterator<const wchar_t*>;
#endif

struct rules
{
    lex_rules _rules;

    rules()
    {
    }

    void push(const char* regex_, const uint16_t id_)
    {
        const char* end_ = regex_ + strlen(regex_);
        lex_string str_(utf8_in_iterator(regex_, end_),
            utf8_in_iterator(end_, end_));

        _rules.push(str_, id_);
    }

    void push(const char* regex_, const uint16_t id_, const uint16_t user_id_)
    {
        const char* end_ = regex_ + strlen(regex_);
        lex_string str_(utf8_in_iterator(regex_, end_),
            utf8_in_iterator(end_, end_));

        _rules.push(str_, id_, user_id_);
    }
};

struct match_results
{
    lex_string _input;
    lex_match _match;

    match_results(const char* input_) :
        _input(utf8_in_iterator(input_, input_ + strlen(input_)),
            utf8_in_iterator(input_ + strlen(input_), input_ + strlen(input_))),
        _match(_input.c_str(), _input.c_str() + _input.size())
    {
    }

    void reset(const char* input_)
    {
        _input.assign(utf8_in_iterator(input_, input_ + strlen(input_)),
            utf8_in_iterator(input_ + strlen(input_), input_ + strlen(input_)));
        _match.first = _input.c_str();
        _match.second = _input.c_str() + _input.size();
    }

    int16_t id() const
    {
        return _match.id;
    }

    int16_t user_id() const
    {
        return _match.user_id;
    }

    std::string str() const
    {
        std::string ret_(utf8_out_iterator(_match.first, _match.second),
            utf8_out_iterator(_match.second, _match.second));

        return ret_;
    }

    bool bol() const
    {
        return _match.bol;
    }

    int16_t state() const
    {
        return _match.state;
    }
};

void build(const rules& rules_, lex_sm& sm_)
{
    lex_generator::build(rules_._rules, sm_);
}

void lookup(const lex_sm& sm_, match_results& results_)
{
    lexertl::lookup(sm_, results_._match);
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
        .def("push",
            static_cast<void (rules::*)
            (const char*, const uint16_t)>
            (&rules::push))
        .def("push",
            static_cast<void (rules::*)
            (const char*, const uint16_t, uint16_t)>
            (&rules::push));

    py::class_<lex_sm>(m, "state_machine")
        .def(py::init<>());

    py::class_<match_results>(m, "match_results")
        .def(py::init<const char*>())
        .def("reset", &match_results::reset)
        .def("id", &match_results::id)
        .def("user_id", &match_results::user_id)
        .def("str", &match_results::str)
        .def("bol", &match_results::bol)
        .def("state", &match_results::state);

    m.def("build", &build);
    m.def("lookup", &lookup);
    m.def("dump", &dump);
}
