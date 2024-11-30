Spring Bean : IoC (Inversion of Control) 컨테이너가 관리하는 객체 

애플리케이션을 구성하는 객체들이 Spring에 의해 생성되고, 의존성이 관리되도록 지원하는 역할

Bean 특징
- 관리 객체 : Spring 컨테이너가 직접 객체의 생성과 생명주기를 관리. 이를 통해 애플리케이션의 비즈니스 로직에만 집중할 수 있음.
- 의존성 주입 : 객체가 필요한 다른 객체(의존성)를 자동으로 주입. 이를 통해 loose coupling을 유지.
- 싱글톤 범위 : Spring은 Bean을 싱글톤으로 관리하므로, 동일 타입의 Bean은 애플리케이션 전역에서 단 하나만 생성되고, 어디서든 동일한 인스턴스를 참조.
- 설정 방법 : xml 설정, java configuration class, @Component, @Service, @Repository 등의 어노테이션을 이용해 정의.

example

```java
// App02HelloWorldSpring.java
package com.hobin.learn_spring;

// Spring의 애플리케이션 컨텍스트를 관리하는 클래스 import
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class App02HelloWorldSpring {

	public static void main(String[] args) {
        // HelloWorldConfiguration 클래스에 정의된 Bean을 불러오는 컨텍스트를 생성
        // context : Bean을 관리하고 제공하는 컨테이너 역할
		var context = 
				new AnnotationConfigApplicationContext(HelloWorldConfiguration.class);
		
        // getBean : context에서 name이라는 Bean을 가져옴
		System.out.println(context.getBean("name"));
	}
}
```

```java
// HelloWorldConfiguration.java
package com.hobin.learn_spring;

// Bean, Configuration 어노테이션 지정을 위한 클래스
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

// @Configuration : Spring 설정 파일로 사용될 것임에 대한 어노테이션
@Configuration
public class HelloWorldConfiguration {
	// @Bean : name() 메서드가 Bean을 생성함을 의미하는 어노테이션 
    // "name"이라는 Bean을 생성 후, 해당 Bean 객체의 값은 "Name!!!"
	@Bean
	public String name() {
		return "Name!!!";
	}
	
}
```

관련 개념
- IoC (Inversion of Control) : 객체 생성 및 관리를 애플리케이션 코드가 아닌, 외부 프레임워크 (ex. Spring)에서 담당하는 것
- DI (Dependency Injection) : IoC 구현 방법 중 하나. 객체가 필요한 의존성을 직접 생성하지 않고, 외부에서 주입하는 방식. 필요한 객체를 외부에서 주입받음으로써 객체 간 결합도가 낮아지고, 코드 재사용성이 높아짐.

DI 구현 방법 : 생성자 주입, Setter 주입, 필드 주입 (@Autowired 같은 어노테이션 사용)

```java
public class Car {
    private Engine engine;
    public Car() {
        this.engine = new Engine();
    }
}
```

위 예제에서 Car가 직접 Engine을 생성함

이를 아래와 같이 DI로 IoC를 사용하면 Car는 Engine에 대한 책임이 없음

```java
public class Car {
    private Engine engine;
    public Car(Engine engine) {
        this.engine = engine;
    }
}
```

------

Spring Bean 에 파라미터 넣기 

```java 
package com.hobin.learn_spring.helloworld;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

record Person(String name, int age, Address addr) {};
record Address(String line, String city, String country) {};

@Configuration
public class HelloWorldConfiguration {
	
	@Bean
	public String name() {
		return "Name!!!";
	}
	
	@Bean
	public int age() {
		return 1;
	}
	
	@Bean
	public Person person() {
		var person = new Person("person!!!", 123, address());
		return person;
	}
	
	@Bean
	public Address address() {
		return new Address("line!!!", "city!!!", "country!!!");
	}
	
	@Bean
	public Person person3Parameters(String name, int age, Address addr) {
		return new Person(name + "123", age, addr);
	}
}
```

person3Parameters Bean에 String, int, Address 에 해당하는 파라미터 사용됨. 

이 때, main에서 직접 파라미터를 넣지 않고 다음과 같이 그냥 호출하여도, 적합한 Bean을 매칭해줌 

```java 
package com.hobin.learn_spring.helloworld;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class App02HelloWorldSpring {

	public static void main(String[] args) {
		// 1. launch a spring context
		var context = 
				new AnnotationConfigApplicationContext(HelloWorldConfiguration.class);
		
		// 2. configure the things that we want Spring to manage
		// HelloWorldConfiguration - @Configuration
		// name - @Bean
		
		// 3. retrieving Beans managed by Spring
		System.out.println(context.getBean("name"));
		
		System.out.println(context.getBean("age"));
	
		System.out.println(context.getBean("person3Parameters"));
	}
}
```

단, 동일한 class 타입인 Bean이 여러 개일 때는 싱글톤 패턴에 위배된다는 에러 발생 

따라서, 파라미터를 받는 것과 같이, 어떤 객체를 가져와야 할 지 모호한 경우를 대비하기 위해 

@Primary annotation과 특정 Bean을 명확히 매칭하기 위해 @Qualifier annotation을 사용함 

또한, Bean에 특정 이름 부여 시, name= 옵션 추가하면 됨.

```java 
package com.hobin.learn_spring.helloworld;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;


record Person(String name, int age, Address addr) {};
record Address(String line, String city, String country) {};

@Configuration
public class HelloWorldConfiguration {
	
	@Bean
	public String name() {
		return "Name!!!";
	}
	
	@Bean
	public int age() {
		return 1;
	}
	
	@Bean
	public Person person() {
		var person = new Person("person!!!", 123, address());
		return person;
	}
	
	@Bean
	@Primary
	public Address address() {
		return new Address("line!!!", "city!!!", "country!!!");
	}
	
	@Bean(name="addr2")
	@Qualifier("addr3qualifier")
	public Address address2() {
		return new Address("line2!!!", "city2!!!", "country2!!!");
	}
	
	@Bean
	@Primary
	public Person person2MethodCall() {
		return new Person(name(), age(), address());
	}
	
	@Bean
	public Person person3Parameters(String name, int age, Address addr) {
		return new Person(name + "123", age, addr);
	}
	
	@Bean
	public Person person4Qualifier(String name, int age, @Qualifier("addr3qualifier") Address addr) {
		return new Person(name, age, addr);
	}
}
```

위와 같은 상황에서

Address 타입인 것은 address, address2 2개가 있음. 

address에 @Primary annotation을 추가함으로써, 

person3Parameters 객체가 나중에 사용될 때, address, address2 중 address가 자동으로 매핑되게 됨. 

그리고 address2에는 @Qualifier annotation을 추가함으로써, 

person4Qualifier에서 파라미터로 넣는 것과 같이, 우선순위와 상관없이, 특정 Bean을 매칭시킬 수 있음 

그리고 string으로 context.getBean("name") 과 같이 직접 지정하는 것 외에 

context.getBean(Person.class) 로 가져올 수 있으며, 해당 클래스 내에 선언된 함수 등도 사용 가능 
