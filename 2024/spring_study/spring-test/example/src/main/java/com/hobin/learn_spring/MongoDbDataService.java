package com.hobin.learn_spring;

import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;

@Component
@Primary
public class MongoDbDataService implements DataService {

    @Override
    public int[] retriveData() {
        return new int[] {11, 22, 33, 44, 55};
    }
}
