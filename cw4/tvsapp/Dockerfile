FROM node:alpine
ENV APP /home/node/app

WORKDIR ${APP}

COPY src ./

RUN npm i

RUN chown -R node /home/node

ENV NODE_PORT 4010

EXPOSE $NODE_PORT

USER node

CMD ["node", "tvsapp.js"]
