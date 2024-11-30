spring boot 프로젝트 만들기

spring과 동일하게 spring initailizr를 이용해 프로젝트를 생성하면 된다.

https://start.spring.io/

그리고 web 서버 구성을 위해 dependencies에서 필요한 걸 추가하여 다운로드 받는다.

(기본 필요 : spring web, devtools)

다운로드한 프로젝트 실행 시, 127.0.0.1:8080에 시간 값이랑 에러 나오는 페이지가 나온다면 정상 동작 중인 것

---

spring boot 프로젝트 생성 시 아래와 같이 기본 파일 생성됨

```java
package com.example.learn_spring_boot;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class LearnSpringBootApplication {

	public static void main(String[] args) {
		SpringApplication.run(LearnSpringBootApplication.class, args);
	}

}
```

간단하게 Course 모델과 이에 대한 컨트롤러를 설정하여 간단한 mvc 패턴을 적용해보면 아래와 같다. 

```java 
// Course.java
package com.example.learn_spring_boot;

public class Course {
    private long id;
    private String name;
    private String author; 

    // Constructor 
    public Course(long id, String name, String author) {
        super();
        this.id = id;
        this.name = name;
        this.author = author;
    }

    // Getter 
    public long getId() {
        return id; 
    }

    public String getName() {
        return name;
    }

    public String getAuthor() {
        return author;
    }

    // toString 
    @Override
    public String toString() {
        return "Course [id = ]" + id + ", name = " + name + ", author = " + author + "]";
    }
}
```

```java 
// CourseController.java

package com.example.learn_spring_boot;

import java.util.Arrays;
import java.util.List;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class CourseController {
    
    @RequestMapping("/courses")
    public List<Course> retrieveAllCourses() {
        return Arrays.asList(
            new Course(1, "Learn 1", "Author 1"),
            new Course(2, "Learn 2", "Author 2")
        );
    }

}
```

@RestController annotation으로 rest api에 대한 컨트롤러임을 명시한다. 

@RequestMapping annotation으로 해당 path로 클라이언트가 request 시 반환될 response 내용을 작성한다. 

기본적으로 response type이 json으로 지정된다. 

따라서 해당 path에 대해 request를 하면 아래와 같은 json 값을 얻을 수 있다. 

```json
[{"id":1,"name":"Learn 1","author":"Author 1"},{"id":2,"name":"Learn 2","author":"Author 2"}]
```

