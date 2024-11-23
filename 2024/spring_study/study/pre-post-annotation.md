@PostConstruct : 기본적 constructor 실행 후, 추가적으로 실행되는 조건들 

@PreDestroy : 해당 객체가 삭제되기 전, 수행되는 작업들

```java
package com.hobin.learn_spring.dependencies.prePost;

import java.util.Arrays;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Component;

import jakarta.annotation.PostConstruct;
import jakarta.annotation.PreDestroy;

@Component
class SomeClass {
	private SomeDependency someDependency;

	public SomeClass(SomeDependency someDependency) {
		super();
		this.someDependency = someDependency;
		System.out.println("All dependencies are ready.");
	}

	@PostConstruct
	public void initialize() {
		someDependency.getReady();
	}

	@PreDestroy
	public void cleanup() {
		System.out.println("Cleanup");
	}
}

@Component
class SomeDependency {
	public void getReady() {
		System.out.println("some logic of dependency");
	}
}

@Configuration
@ComponentScan
public class PrePostAnnotations {

	public static void main(String[] args) {
		try(var context = new AnnotationConfigApplicationContext(
			PrePostAnnotations.class
		)) {
			Arrays.stream(context.getBeanDefinitionNames()).forEach(System.out::println);
		}
	}
}
```

위 내용 실행 시 다음과 같음

```
All dependencies are ready.
some logic of dependency
org.springframework.context.annotation.internalConfigurationAnnotationProcessor
org.springframework.context.annotation.internalAutowiredAnnotationProcessor
org.springframework.context.annotation.internalCommonAnnotationProcessor
org.springframework.context.event.internalEventListenerProcessor
org.springframework.context.event.internalEventListenerFactory
prePostAnnotations
someClass
someDependency
Cleanup
```

기본 constructor 실행 시, All ~ 출력 후, PostConstruct annotation에 따라 some logic ~ 가 출력된다. 

그리고 프로그램 종료 시, getBeanDefinitionNames 로 호출된 SomeClass가 삭제되며,
그 직전에 PreDestroy annotation에 따라 Cleanup을 마지막으로 출력한다. 


