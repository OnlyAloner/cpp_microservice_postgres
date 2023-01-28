#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"
#include <vector>
#include <iostream>

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "storage/postgres/Postgres.hpp"
#include "storage/postgres/crud/Crud.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
private:
  CPostgres* m_postgres;

public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<CPostgres>, postgres), OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper),
      m_postgres(postgres.get())
  {
  }
  ~MyController() {
  }
public:
  

  ENDPOINT("POST", "/names", addName) {
    auto resp = m_postgres->GetCrud()->Create("Something-New");

    if (resp.second != nullptr) {
      std::cout << "Error\n";
      return createResponse(Status::CODE_500, "Internal Server Error");
    }

    std::cout << resp.first << '\n';

    return createResponse(Status::CODE_200, "OK");
  }

  ENDPOINT("GET", "/names", getNames) {
    auto resp = m_postgres->GetCrud()->GetList();
    if (resp.second != nullptr) {
      std::cout << "Error\n";
      return createResponse(Status::CODE_500, "Internal Server Error");
    }

    // std::cout << resp.first.size() << '\n';

    auto dto = NamesDto::createShared();
    dto->statusCode = 200;
    dto->names = {};

    for (int i=0; i<resp.first.size(); i++) {
      dto->names->push_back(resp.first[i].name);
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
