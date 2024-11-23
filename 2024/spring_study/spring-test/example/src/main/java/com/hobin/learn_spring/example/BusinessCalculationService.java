package com.hobin.learn_spring.example;

import java.util.Arrays;

import org.springframework.stereotype.Component;

@Component
public class BusinessCalculationService {

    private DataService dataService;

    // Constructor
    public BusinessCalculationService(DataService dataService) {
        super();
        this.dataService = dataService;
    }

    public int findMax() {
        return Arrays.stream(dataService.retriveData()).max().orElse(0);
    }
}
