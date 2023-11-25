import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import sensor, binary_sensor
from esphome.const import CONF_ID, CONF_MAC_ADDRESS

# Configuration schema
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PersonalToolbox),
    cv.Required(CONF_MAC_ADDRESS): cv.mac_address,
}).extend(cv.COMPONENT_SCHEMA)

# Code generation
def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)
    yield binary_sensor.register_binary_sensor(var, config)