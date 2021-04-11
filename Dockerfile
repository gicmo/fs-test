FROM alpine:edge
RUN apk upgrade -a \
    && apk add --no-cache gcc findmnt musl-dev
RUN mkdir /code
ADD empty-dir.c /code
ADD test.sh /code
WORKDIR /code
CMD ["/code/test.sh"]