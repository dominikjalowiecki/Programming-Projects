package com.dj.BDDproject;

import com.dj.BDDproject.factory.CarFactory;
import com.dj.BDDproject.model.car.CarType;

/**
 * https://bulldogjob.pl/readme/czy-testy-jednostkowe-w-javie-moga-stanowic-dokumentacje-projektowa
 */
public class App 
{
    public static void main( String[] args )
    {
    	CarFactory carFactory = new CarFactory();
		System.out.println(carFactory.createCar(CarType.LIMOUSINE));
    }
}
