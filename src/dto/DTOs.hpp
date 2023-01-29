#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class MyDto : public oatpp::DTO {
  
  DTO_INIT(MyDto, DTO)
  
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
  
};

class NameDto : public oatpp::DTO {
  
  DTO_INIT(NameDto, DTO)
  
  DTO_FIELD(String, name);
  
};

class NamesDto : public oatpp::DTO {
    
  DTO_INIT(NamesDto, DTO)
    
  DTO_FIELD(Vector<String>, names);
    
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */
