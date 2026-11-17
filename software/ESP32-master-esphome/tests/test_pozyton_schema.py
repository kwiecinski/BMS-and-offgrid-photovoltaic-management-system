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

    def test_eabm_tangent_has_no_default_unit_or_device_class(self):
        config = self.meter(
            "EABM", "456 1234567",
            sensors={"neutral_tangent": {"name": "EABM Neutral Tangent"}},
        )
        tangent = config["sensors"]["neutral_tangent"]
        self.assertNotIn("unit_of_measurement", tangent)
        self.assertNotIn("device_class", tangent)
        self.assertEqual(tangent["state_class"], "measurement")

    def test_seab_tangent_is_rejected(self):
        with self.assertRaisesRegex(cv.Invalid, "documented for EABM only"):
            self.meter(
                "SEAB", "123.4567890",
                sensors={"neutral_tangent": {"name": "SEAB Neutral Tangent"}},
            )


if __name__ == "__main__":
    unittest.main()
