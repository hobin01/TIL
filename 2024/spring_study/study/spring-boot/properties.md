src/main/resources/application.properties 파일 이용해 다양한 설정이 가능

로깅 레벨 : trace > debug > info > warning > error > off

properties 파일을 dev, prod, qa 등 다양한 환경에 맞게 설정 가능

기존 properties 파일 이름에 -dev, -prod 등을 추가하면 됨

- application-dev.properties
```
spring.application.name=learn-spring-boot
logging.level.org.springframework=trace
```

- application-prod.properties
```
spring.application.name=learn-spring-boot
logging.level.org.springframework=info
```

- application.properties
- 애플리케이션 실행 시 따라가는 properties 내용
```
spring.application.name=learn-spring-boot
logging.level.org.springframework=debug
spring.profiles.active=prod
```

위와 같이 spring.profiles.active=prod 처럼 어떤 프로파일 내용을 실행할 지를 명시할 수 있음

위 예시는 prod 프로파일을 실행해라는 뜻이므로, application-prod.properties 파일에 따라 실행됨

따라서 info 레벨의 로깅이 spring 앱 실행 시 진행

------

properties 파일에 기본값을 설정하여 configuration 설정하기

```java
// CurrencyServiceConfiguration.java

package com.example.learn_spring_boot;

import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

// currency-service.url
// currency-service.username
// currency-service.key 

@ConfigurationProperties(prefix="currency-service")
@Component
public class CurrencyServiceConfiguration {
    
    private String url;
    private String username;
    private String key;

    public String getUrl() {
        return this.url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUsername() {
        return this.username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getKey() {
        return this.key;
    }

    public void setKey(String key) {
        this.key = key;
    }
}
```

```java
// CurrencyServiceController.java
package com.example.learn_spring_boot;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class CurrencyServiceController {
    
    @Autowired
    private CurrencyServiceConfiguration configuration;

    @RequestMapping("/currency-configuration")
    public CurrencyServiceConfiguration retrieve() {
        return configuration;
    }
}
```

- application.properties
```
spring.application.name=learn-spring-boot
logging.level.org.springframework=debug

currency-service.url=http://default.com
currency-service.username=default-username
currency-service.key=default-key
```

현재 CurrencyServiceConfiguration.java 에서 별도 constructor를 지정하지 않음

@ConfigurationProperties annotation으로 properties 파일에 지정한 디폴트 값을 가져와 매핑할 수 있음

prefix= 에 해당하는 값을 application.properties에서 읽어 각 값에 매핑함. 

단, application.properties에서 spring.profiles.active=prod 와 같이 특정 프로파일을 실행하도록 지정하면

해당 프로파일에서 지정된 값으로 매칭됨. 

또한 해당 클래스에 대해 별도 constructor가 없으므로, getter, setter를 지정해야 함. 

테스트를 위해 해당 클래스에 대해 @Component로 컴포넌트로 지정하고, 

CurrencyServiceController.java에서 spring bean으로 관리되는 CurrencyServiceConfiguration 컴포넌트 사용을 위해 Autowired annotation을 추가한 다음, 

(Autowired는 기본적으로 Bean으로 등록된 것 중 가져옴. 따라서, Component와 같이 Bean으로 관리되도록 하는 것이 필수. 그렇지 않은 것에 대해 Autowired 적용 시, required=False 처리를 하거나, 에러가 나거나 해야 함.)

127.0.0.1:8080/currency-configuration 으로 접속하면 다음과 같이 response를 받을 수 있음

```
{"url":"http://default.com","username":"default-username","key":"default-key"}
```

(컴포넌트는 spring 컨테이너에 의해 관리되는 Bean 객체를 의미)

spring에서는 컴포넌트를 사용하려면 ComponentScan을 해야 하지만, spring boot에서는 @SpringBootApplication annotation에 해당 기능이 포함되어 있기 떄문에 별도 scan 기능 없이 사용 가능

그리고 CurrencyServiceController class의 경우, RestController만 등록하고, Component 지정을 안 했지만, RestController == Controller + ResponseBody 이고, Controller > Component 이므로

Component 기능을 이미 포함하고 있음 

