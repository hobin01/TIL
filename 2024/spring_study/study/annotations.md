자주 사용되는 annotation 정리 

Spring Core

@Component
- Spring 컨테이너에 의해 관리되는 Bean을 정의 

@Service
- 비즈니스 로직 계층을 의미. @Component의 특화된 형태 

@Repository
- 데이터 엑세스 계층 (DAO)를 의미. @Component의 특화된 형태

@Controller
- MVC 패턴의 컨트롤러를 정의

@RestController
- @Controller + @ResponseBody의 형태. Restful 웹 서비스를 위한 컨트롤러

@Autowired
- 의존성 주입을 위해 사용 


Spring Boot

@SpringBootApplication
- Spring Boot 애플리케이션의 시작점. @Configuration, @EnableAutoConfiguration, @ComponentScan을 포함

@Configuration
- Java 기반 설정 클래스임을 의미

@ComponentScan
- 스캔할 패키지를 지정하여 Bean으로 등록 

@EnableAutoConfiguration
- Spring Boot의 자동 설정 기능을 활성화 


Web

@RequestMapping
- http 요청 url을 메서드와 매핑 

@GetMapping
- get 요청을 처리 

@PostMapping
- post 요청을 처리 

@PutMapping
- put 요청을 처리 

@DeleteMapping
- delete 요청을 처리 

@PathVariable
- url path와 메서드 파라미터를 매핑

@RequestParam
- 쿼리 파라미터를 메서드 파라미터로 매핑

@RequestBody
- http request를 Java 객체로 변환 

@ResponseBody
- 메서드 반환값을 http 응답으로 변환 


Spring Data JPA

@Entity
- 데이터베이스 테이블과 매핑되는 JPA 엔티티 클래스 

@Table
- 엔티티와 매핑될 데이터베이스 테이블의 세부 정보를 정의

@Id
- 데이터베이스 테이블의 기본 키를 의미 

@GeneratedValue
- 기본 키 생성 전략을 지정 

@ManyToOne / @OneToMany / @ManyToMany / @OnetoOne
- 엔티티 간 관계를 매핑


Validation

@Valid
- 객체 유효성 검사 

@NotNull / @NotEmpty / @Size 
- 필드 유효성 검증 


Spring Security

@EnableWebSecurity
- Spring Security 활성화 

@PreAuthorize
- 메서드 실행 전 권환을 확인 

@Secured
- 메서드 레벨에서 특정 역할을 요구 


Spring Boot Actuator

@Endpoint
- 커스텀 actuator 엔드포인트 정의


Configuration Properties

@Value
- application.properties에서 값을 주입 

@ConfigurationProperties
- application.properties의 값을 POJO에 매핑


AOP

@Aspect
- AOP에서 공통 기능을 정의 

@Before / @After / @Around
- 메서드 실행 전 / 후 / 주변에 수행할 작업 정의 


Test

@SpringBootTest
- 통합 테스트를 위한 어노테이션

@WebMvcTest
- Spring MVC 테스트를 위한 어노테이션

@MockBean
- 테스트 시, 의존성을 Mock으로 주입 

@Test
- JUnit의 테스트 메서드 정의 



