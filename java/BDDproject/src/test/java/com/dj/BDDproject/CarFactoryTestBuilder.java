package com.dj.BDDproject;

import static org.assertj.core.api.Assertions.*;

import com.dj.BDDproject.factory.CarFactory;
import com.dj.BDDproject.model.car.Car;
import com.dj.BDDproject.model.car.CarType;

public class CarFactoryTestBuilder {
	private CarFactory carFactory;
	
	private Car car;
	
	private CarFactoryTestBuilder() {}
	
	public static Given given() {
		return new CarFactoryTestBuilder().buildGiven();
	}
	
	private Given buildGiven() {
		return new Given();
	}
	
	public class Given {
		public Given thereIsACarFactory() {
			carFactory = new CarFactory();
			return this;
		}
		
		public When when() {
			return new When();
		}
	}
	
	public class When {
		public When sportFerrariCarCreated() {
			car = carFactory.createCar(CarType.SPORT);
			return this;
		}
		
		public Then then() {
			return new Then();
		}
	}
	
	public class Then {
		public Then brandShouldBe(String carBrand) {
			assertThat(car.getBrand())
				.as("Car brand should be " + carBrand)
				.isEqualTo(carBrand);
			return this;
		}
		
		public Then engineSizeShouldBe(float engineSize) {
			assertThat(car.getEngineSize())
				.as("Engine size should be " + engineSize)
				.isEqualTo(engineSize);
			return this;
		}
		
		public Then doorsCountShouldBe(int doorsCount) {
			assertThat(car.getDoorsCount())
				.as("Doors count should be " + doorsCount)
				.isEqualTo(doorsCount);
			return this;
		}
		
		public Then carTypeShouldBe(CarType carType) {
			assertThat(car.getCarType())
				.as("Car type should be " + carType)
				.isEqualTo(carType);
			return this;
		}
	}
}
