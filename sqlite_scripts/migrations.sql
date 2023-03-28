-- Таблица викторин
CREATE TABLE IF NOT EXISTS quizzes (
  id INTEGER PRIMARY KEY, -- Идентификатор текущей таблицы
  explanation TEXT NOT NULL, -- Подсказка
  question TEXT NOT NULL, -- Вопрос
  answer_true TEXT NOT NULL, -- Правильный ответ
  answer_false_one TEXT NOT NULL, -- Не правильный ответ
  answer_false_two TEXT NOT NULL, -- Не правильный ответ
  answer_false_three TEXT NOT NULL -- Не правильный ответ
);

-- Таблица чатов телеграм
CREATE TABLE IF NOT EXISTS chats (
  chat_id INTEGER PRIMARY KEY, -- Идентификатор текущей таблицы
  name TEXT NOT NULL, -- Название чата в телеграм
  username TEXT NOT NULL, -- Username чата в телеграм
  is_active INTEGER NOT NULL -- Активность в чате
);

-- Таблица-мост между викториной и чатом
CREATE TABLE IF NOT EXISTS quizzes_and_chats (
  quiz_id INTEGER, -- Идентификатор таблицы quizzes.id
  chat_id INTEGER, -- Идентификатор таблицы chats.chat_id
  FOREIGN KEY (quiz_id) REFERENCES quizzes(id), -- связь с таблицей quizzes
  FOREIGN KEY (chat_id) REFERENCES chats(chat_id) -- связь с таблицей chats
);
