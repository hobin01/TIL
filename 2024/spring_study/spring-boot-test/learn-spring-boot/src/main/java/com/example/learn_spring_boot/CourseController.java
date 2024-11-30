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
            new Course(2, "Learn 2", "Author 2"),
            new Course(2, "Learn 3", "Author 3")
        );
    }

}
