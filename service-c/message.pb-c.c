/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: message.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "message.pb-c.h"
void   hero_msg__init
                     (HeroMsg         *message)
{
  static HeroMsg init_value = HERO_MSG__INIT;
  *message = init_value;
}
size_t hero_msg__get_packed_size
                     (const HeroMsg *message)
{
  assert(message->base.descriptor == &hero_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t hero_msg__pack
                     (const HeroMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &hero_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t hero_msg__pack_to_buffer
                     (const HeroMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &hero_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
HeroMsg *
       hero_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (HeroMsg *)
     protobuf_c_message_unpack (&hero_msg__descriptor,
                                allocator, len, data);
}
void   hero_msg__free_unpacked
                     (HeroMsg *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &hero_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   heart_beat__init
                     (HeartBeat         *message)
{
  static HeartBeat init_value = HEART_BEAT__INIT;
  *message = init_value;
}
size_t heart_beat__get_packed_size
                     (const HeartBeat *message)
{
  assert(message->base.descriptor == &heart_beat__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t heart_beat__pack
                     (const HeartBeat *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &heart_beat__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t heart_beat__pack_to_buffer
                     (const HeartBeat *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &heart_beat__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
HeartBeat *
       heart_beat__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (HeartBeat *)
     protobuf_c_message_unpack (&heart_beat__descriptor,
                                allocator, len, data);
}
void   heart_beat__free_unpacked
                     (HeartBeat *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &heart_beat__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   login_req__init
                     (LoginReq         *message)
{
  static LoginReq init_value = LOGIN_REQ__INIT;
  *message = init_value;
}
size_t login_req__get_packed_size
                     (const LoginReq *message)
{
  assert(message->base.descriptor == &login_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t login_req__pack
                     (const LoginReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &login_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t login_req__pack_to_buffer
                     (const LoginReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &login_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
LoginReq *
       login_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (LoginReq *)
     protobuf_c_message_unpack (&login_req__descriptor,
                                allocator, len, data);
}
void   login_req__free_unpacked
                     (LoginReq *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &login_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   connect_req__init
                     (ConnectReq         *message)
{
  static ConnectReq init_value = CONNECT_REQ__INIT;
  *message = init_value;
}
size_t connect_req__get_packed_size
                     (const ConnectReq *message)
{
  assert(message->base.descriptor == &connect_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t connect_req__pack
                     (const ConnectReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &connect_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t connect_req__pack_to_buffer
                     (const ConnectReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &connect_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnectReq *
       connect_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnectReq *)
     protobuf_c_message_unpack (&connect_req__descriptor,
                                allocator, len, data);
}
void   connect_req__free_unpacked
                     (ConnectReq *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &connect_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   login_rsp__init
                     (LoginRsp         *message)
{
  static LoginRsp init_value = LOGIN_RSP__INIT;
  *message = init_value;
}
size_t login_rsp__get_packed_size
                     (const LoginRsp *message)
{
  assert(message->base.descriptor == &login_rsp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t login_rsp__pack
                     (const LoginRsp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &login_rsp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t login_rsp__pack_to_buffer
                     (const LoginRsp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &login_rsp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
LoginRsp *
       login_rsp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (LoginRsp *)
     protobuf_c_message_unpack (&login_rsp__descriptor,
                                allocator, len, data);
}
void   login_rsp__free_unpacked
                     (LoginRsp *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &login_rsp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   connect_rsp__init
                     (ConnectRsp         *message)
{
  static ConnectRsp init_value = CONNECT_RSP__INIT;
  *message = init_value;
}
size_t connect_rsp__get_packed_size
                     (const ConnectRsp *message)
{
  assert(message->base.descriptor == &connect_rsp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t connect_rsp__pack
                     (const ConnectRsp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &connect_rsp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t connect_rsp__pack_to_buffer
                     (const ConnectRsp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &connect_rsp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnectRsp *
       connect_rsp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnectRsp *)
     protobuf_c_message_unpack (&connect_rsp__descriptor,
                                allocator, len, data);
}
void   connect_rsp__free_unpacked
                     (ConnectRsp *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &connect_rsp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   enemy_msg__init
                     (EnemyMsg         *message)
{
  static EnemyMsg init_value = ENEMY_MSG__INIT;
  *message = init_value;
}
size_t enemy_msg__get_packed_size
                     (const EnemyMsg *message)
{
  assert(message->base.descriptor == &enemy_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t enemy_msg__pack
                     (const EnemyMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &enemy_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t enemy_msg__pack_to_buffer
                     (const EnemyMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &enemy_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
EnemyMsg *
       enemy_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (EnemyMsg *)
     protobuf_c_message_unpack (&enemy_msg__descriptor,
                                allocator, len, data);
}
void   enemy_msg__free_unpacked
                     (EnemyMsg *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &enemy_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   new_enemy__init
                     (NewEnemy         *message)
{
  static NewEnemy init_value = NEW_ENEMY__INIT;
  *message = init_value;
}
size_t new_enemy__get_packed_size
                     (const NewEnemy *message)
{
  assert(message->base.descriptor == &new_enemy__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t new_enemy__pack
                     (const NewEnemy *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &new_enemy__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t new_enemy__pack_to_buffer
                     (const NewEnemy *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &new_enemy__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
NewEnemy *
       new_enemy__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (NewEnemy *)
     protobuf_c_message_unpack (&new_enemy__descriptor,
                                allocator, len, data);
}
void   new_enemy__free_unpacked
                     (NewEnemy *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &new_enemy__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   game_start__init
                     (GameStart         *message)
{
  static GameStart init_value = GAME_START__INIT;
  *message = init_value;
}
size_t game_start__get_packed_size
                     (const GameStart *message)
{
  assert(message->base.descriptor == &game_start__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t game_start__pack
                     (const GameStart *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &game_start__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t game_start__pack_to_buffer
                     (const GameStart *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &game_start__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
GameStart *
       game_start__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (GameStart *)
     protobuf_c_message_unpack (&game_start__descriptor,
                                allocator, len, data);
}
void   game_start__free_unpacked
                     (GameStart *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &game_start__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor hero_msg__field_descriptors[3] =
{
  {
    "uid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(HeroMsg, uid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_x",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(HeroMsg, point_x),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_y",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(HeroMsg, point_y),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned hero_msg__field_indices_by_name[] = {
  1,   /* field[1] = point_x */
  2,   /* field[2] = point_y */
  0,   /* field[0] = uid */
};
static const ProtobufCIntRange hero_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor hero_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Hero_msg",
  "HeroMsg",
  "HeroMsg",
  "",
  sizeof(HeroMsg),
  3,
  hero_msg__field_descriptors,
  hero_msg__field_indices_by_name,
  1,  hero_msg__number_ranges,
  (ProtobufCMessageInit) hero_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define heart_beat__field_descriptors NULL
#define heart_beat__field_indices_by_name NULL
#define heart_beat__number_ranges NULL
const ProtobufCMessageDescriptor heart_beat__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Heart_beat",
  "HeartBeat",
  "HeartBeat",
  "",
  sizeof(HeartBeat),
  0,
  heart_beat__field_descriptors,
  heart_beat__field_indices_by_name,
  0,  heart_beat__number_ranges,
  (ProtobufCMessageInit) heart_beat__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor login_req__field_descriptors[1] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(LoginReq, name),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned login_req__field_indices_by_name[] = {
  0,   /* field[0] = name */
};
static const ProtobufCIntRange login_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor login_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Login_req",
  "LoginReq",
  "LoginReq",
  "",
  sizeof(LoginReq),
  1,
  login_req__field_descriptors,
  login_req__field_indices_by_name,
  1,  login_req__number_ranges,
  (ProtobufCMessageInit) login_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define connect_req__field_descriptors NULL
#define connect_req__field_indices_by_name NULL
#define connect_req__number_ranges NULL
const ProtobufCMessageDescriptor connect_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Connect_req",
  "ConnectReq",
  "ConnectReq",
  "",
  sizeof(ConnectReq),
  0,
  connect_req__field_descriptors,
  connect_req__field_indices_by_name,
  0,  connect_req__number_ranges,
  (ProtobufCMessageInit) connect_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor login_rsp__field_descriptors[5] =
{
  {
    "success",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(LoginRsp, success),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_x",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(LoginRsp, point_x),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_y",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(LoginRsp, point_y),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "enemy_num",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(LoginRsp, enemy_num),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uid",
    5,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(LoginRsp, uid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned login_rsp__field_indices_by_name[] = {
  3,   /* field[3] = enemy_num */
  1,   /* field[1] = point_x */
  2,   /* field[2] = point_y */
  0,   /* field[0] = success */
  4,   /* field[4] = uid */
};
static const ProtobufCIntRange login_rsp__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor login_rsp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Login_rsp",
  "LoginRsp",
  "LoginRsp",
  "",
  sizeof(LoginRsp),
  5,
  login_rsp__field_descriptors,
  login_rsp__field_indices_by_name,
  1,  login_rsp__number_ranges,
  (ProtobufCMessageInit) login_rsp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor connect_rsp__field_descriptors[1] =
{
  {
    "success",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(ConnectRsp, success),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned connect_rsp__field_indices_by_name[] = {
  0,   /* field[0] = success */
};
static const ProtobufCIntRange connect_rsp__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor connect_rsp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Connect_rsp",
  "ConnectRsp",
  "ConnectRsp",
  "",
  sizeof(ConnectRsp),
  1,
  connect_rsp__field_descriptors,
  connect_rsp__field_indices_by_name,
  1,  connect_rsp__number_ranges,
  (ProtobufCMessageInit) connect_rsp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor enemy_msg__field_descriptors[3] =
{
  {
    "uid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(EnemyMsg, uid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_x",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(EnemyMsg, point_x),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_y",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(EnemyMsg, point_y),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned enemy_msg__field_indices_by_name[] = {
  1,   /* field[1] = point_x */
  2,   /* field[2] = point_y */
  0,   /* field[0] = uid */
};
static const ProtobufCIntRange enemy_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor enemy_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Enemy_msg",
  "EnemyMsg",
  "EnemyMsg",
  "",
  sizeof(EnemyMsg),
  3,
  enemy_msg__field_descriptors,
  enemy_msg__field_indices_by_name,
  1,  enemy_msg__number_ranges,
  (ProtobufCMessageInit) enemy_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor new_enemy__field_descriptors[3] =
{
  {
    "uid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(NewEnemy, uid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_x",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(NewEnemy, point_x),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "point_y",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(NewEnemy, point_y),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned new_enemy__field_indices_by_name[] = {
  1,   /* field[1] = point_x */
  2,   /* field[2] = point_y */
  0,   /* field[0] = uid */
};
static const ProtobufCIntRange new_enemy__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor new_enemy__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "New_enemy",
  "NewEnemy",
  "NewEnemy",
  "",
  sizeof(NewEnemy),
  3,
  new_enemy__field_descriptors,
  new_enemy__field_indices_by_name,
  1,  new_enemy__number_ranges,
  (ProtobufCMessageInit) new_enemy__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define game_start__field_descriptors NULL
#define game_start__field_indices_by_name NULL
#define game_start__number_ranges NULL
const ProtobufCMessageDescriptor game_start__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Game_start",
  "GameStart",
  "GameStart",
  "",
  sizeof(GameStart),
  0,
  game_start__field_descriptors,
  game_start__field_indices_by_name,
  0,  game_start__number_ranges,
  (ProtobufCMessageInit) game_start__init,
  NULL,NULL,NULL    /* reserved[123] */
};
