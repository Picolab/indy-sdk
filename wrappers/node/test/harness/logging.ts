
import * as winston from 'winston'

const winston_config = {
  level:'debug',
  transports: [
    new (winston.transports.Console)()
  ]
}

export const logger = new (winston.Logger)(winston_config)
