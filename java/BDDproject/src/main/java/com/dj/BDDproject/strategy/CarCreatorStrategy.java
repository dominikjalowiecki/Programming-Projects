package com.dj.BDDproject.strategy;

import com.dj.BDDproject.model.car.Car;
import com.dj.BDDproject.model.car.CarType;

public interface CarCreatorStrategy {
	Car createCar();
	
	CarType getCarType();
}
