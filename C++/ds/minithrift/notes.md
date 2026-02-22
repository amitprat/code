# code structure
```
SimpleIDLCompiler/
├─ idl_parser.h
├─ idl_parser.cpp
├─ codegen.h
├─ codegen.cpp
├─ CodeBuilder.h
├─ main.cpp
├─ user.idl
├─ generated/       # output folder
│   ├─ User.h
│   └─ User.cpp
```


# Template-based code generation

- Use a template engine like:
- C++: inja (JSON-based templating)
- Example template for a struct:
```
#pragma once
#include <string>
#include <ostream>
#include <istream>
class {{struct_name}} {
public:
{% for field in fields %}
    {{field.type}} {{field.name}};
{% endfor %}

    void serialize(std::ostream& os) const {
    {% for field in fields %}
        // serialization code for {{field.name}}
    {% endfor %}
    }
};
```