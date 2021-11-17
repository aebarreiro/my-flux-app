FROM alpine as build-env

RUN apk add --no-cache build-base

RUN mkdir -p /src /app

COPY src/*.c /src
RUN gcc -o /app/info_server /src/*.c

## Generate smaller image
FROM alpine

RUN mkdir -p /app
COPY --from=build-env /app/* /app

WORKDIR /app
EXPOSE 3945

ENTRYPOINT [ "./info_server" ]
