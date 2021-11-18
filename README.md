# Åboat VRGP adapter

This repository contains the code for the `adapter` service that translates
calls from the [VRGP specification](https://github.com/aboamare/vrgp-specifications) into Åboat specific calls. This is only
needed for the Åboat, since the [VRGP service](https://github.com/RemoteBoatX/vrgp-service) implementation is supposed to be
as generic as possible. Other boats can directly hook into the VRGP service,
but since Åboat has its own communication protocol, it has to be adapted to
the VRGP protocol.
