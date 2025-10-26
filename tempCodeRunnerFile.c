case '+': case '-': case '*': case '/': case '=':
                    printf("<%c> : Operator\n", c);
                    break;
                case '>': case '<':
                    printf("<%s> : Relational Operator\n");
                    break;
                case ';': case ',': case '(': case ')': case '{': case '}':
                    printf("<%c> : Delimiter\n", c);
                    break;
                default:
                    printf("<%c> : Unknown\n", c);