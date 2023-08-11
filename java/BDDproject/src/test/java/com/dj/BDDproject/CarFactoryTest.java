package com.dj.BDDproject;

import org.junit.Test;

import com.dj.BDDproject.model.car.CarType;

public class CarFactoryTest {
	
	@Test
	public void shouldCreateSportFerrariCar() {
//		// given
//		// There is a car factory
//		CarFactory carFactory = new CarFactory();
//		Car expectedCar = new SportCar(2, 3.0F, "Ferrari");
//		
//		// when
//		// Create Sport car
//		Car createdCar = carFactory.createCar(CarType.SPORT);
//		
//		// then
//		// Ferrari will be produced
//		assertThat(createdCar)
//			.as("Created car should be exactly as expected")
//			.isEqualToComparingFieldByField(expectedCar);
		
		CarFactoryTestBuilder.given()
			.thereIsACarFactory()
		.when()
			.sportFerrariCarCreated()
		.then()
			.brandShouldBe("Ferrari")
			.engineSizeShouldBe(3.0F)
			.doorsCountShouldBe(2)
			.carTypeShouldBe(CarType.SPORT);
	}

}
