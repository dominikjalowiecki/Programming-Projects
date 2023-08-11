package com.dj.BDDproject.factory;

import java.util.ArrayList;
import java.util.List;

import com.dj.BDDproject.model.car.Car;
import com.dj.BDDproject.model.car.CarType;
import com.dj.BDDproject.strategy.CarCreatorStrategy;
import com.dj.BDDproject.strategy.FamilyCarCreatorStrategy;
import com.dj.BDDproject.strategy.LimousineCarCreatorStrategy;
import com.dj.BDDproject.strategy.SportCarCreatorStrategy;
import com.dj.BDDproject.strategy.TruckCarCreatorStrategy;

public class CarFactory {
	private final List<CarCreatorStrategy> strategies = new ArrayList<CarCreatorStrategy>();
	
	public CarFactory() {
		strategies.add(new FamilyCarCreatorStrategy());
		strategies.add(new SportCarCreatorStrategy());
		strategies.add(new TruckCarCreatorStrategy());
		strategies.add(new LimousineCarCreatorStrategy());
	}
	
	public Car createCar(CarType carType) {
		for (CarCreatorStrategy strategy : strategies) {
			if(carType == strategy.getCarType()) {
				return strategy.createCar();
			}
		}
		
		throw new IllegalArgumentException("Invalid car type " + carType);
	}
}

