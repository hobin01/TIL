package com.hobin.learn_spring.example;

import org.springframework.stereotype.Component;

@Component
public class MySQLDataService implements DataService {

    @Override
    public int[] retriveData() {
        return new int[] {1, 2, 3, 4, 5};
    }
}
