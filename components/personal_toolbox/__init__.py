import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import sensor
from esphome.const import CONF_ID

# Configuration schema
personal_toolbox_ns = cg.esphome_ns.namespace("personal_toolbox")
PersonalToolbox = personal_toolbox_ns.class_("PersonalToolbox", cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PersonalToolbox),
}).extend(cv.COMPONENT_SCHEMA)

# Code generation
def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)