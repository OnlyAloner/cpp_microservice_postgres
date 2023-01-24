#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"
#include <vector>

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
private:
  std::vector<std::string> m_names;

public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT("POST", "/names", addName, BODY_DTO(Object<NameDto>, nameDto)) {
    m_names.push_back(nameDto->name);
    return createResponse(Status::CODE_200, "OK");
  }

  ENDPOINT("GET", "/names", getNames) {
    auto dto = NamesDto::createShared();
    dto->statusCode = 200;
    dto->names = {};
    for (auto x:m_names) {
      dto->names->push_back(x);
    }
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  ENDPOINT("GET", "/", root) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("GET", "/here", here) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello buddy!";
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
