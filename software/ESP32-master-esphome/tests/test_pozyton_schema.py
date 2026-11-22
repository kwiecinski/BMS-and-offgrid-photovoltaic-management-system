"""Run with the Python environment containing the target ESPHome version."""

import unittest

import esphome.config_validation as cv
from esphome.core import CORE

from custom_components.pozyton_energy_meters import METER_SCHEMA


class MeterSchemaTest(unittest.TestCase):
    def setUp(self):
        CORE.reset()

    def meter(self, model, address, **extra):
        return METER_SCHEMA(
            dict(meter_name=model.lower(), model=model, address=address, **extra)
        )

    def test_model_specific_addresses(self):
        self.meter("SEAB", "123.4567890")
        self.meter("EABM", "456 1234567")
        for model, address in [("SEAB", "456 1234567"), ("EABM", "123.4567890")]:
            with self.subTest(model=model), self.assertRaisesRegex(
                cv.Invalid, "address must use format"
            ):
                self.meter(model, address)

    def test_neutral_tangent_is_unsupported(self):
        for model, address in [("SEAB", "123.4567890"), ("EABM", "456 1234567")]:
            with self.subTest(model=model), self.assertRaises(cv.Invalid):
                self.meter(model, address, sensors={"neutral_tangent": {"name": "Neutral Tangent"}})

    def test_reactive_power_configuration_depends_on_model(self):
        total = {"reactive_power_total": {"name": "Reactive Power Total"}}
        phases = {f"reactive_power_l{phase}": {"name": f"Reactive Power L{phase}"} for phase in range(1, 4)}
        self.meter("EABM", "456 1234567", sensors=total)
        self.meter("SEAB", "123.4567890", sensors=phases)
        for key, sensor in phases.items():
            with self.subTest(key=key), self.assertRaisesRegex(cv.Invalid, "reactive_power_total"):
                self.meter("EABM", "456 1234567", sensors={key: {"name": "EABM " + sensor["name"]}})


if __name__ == "__main__":
    unittest.main()
